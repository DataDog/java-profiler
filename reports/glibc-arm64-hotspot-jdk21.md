---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-18 21:27:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 13 |
| Allocations | 83 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1792372873 46
1792372878 46
1792372883 46
1792372888 46
1792372893 46
1792372898 46
1792372903 48
1792372908 48
1792372913 48
1792372918 48
1792372923 48
1792372928 48
1792372933 48
1792372938 48
1792372943 48
1792372948 48
1792372953 48
1792372958 48
1792372963 48
1792372968 48
```
</details>

---

