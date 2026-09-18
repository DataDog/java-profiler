---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 09:50:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 286 |
| Sample Rate | 4.77/sec |
| Health Score | 298% |
| Threads | 9 |
| Allocations | 119 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 13 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (3 unique values: 28-40 cores)</summary>

```
1789738906 36
1789738911 36
1789738916 36
1789738921 36
1789738926 36
1789738931 36
1789738936 36
1789738941 36
1789738946 36
1789738951 36
1789738956 36
1789738961 36
1789738966 36
1789738972 28
1789738977 28
1789738982 28
1789738987 28
1789738992 28
1789738997 28
1789739002 28
```
</details>

---

