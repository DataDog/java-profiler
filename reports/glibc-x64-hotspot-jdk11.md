---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-17 16:32:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 636 |
| Sample Rate | 10.60/sec |
| Health Score | 662% |
| Threads | 8 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1128 |
| Sample Rate | 18.80/sec |
| Health Score | 1175% |
| Threads | 10 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (2 unique values: 56-64 cores)</summary>

```
1789676870 56
1789676875 56
1789676880 56
1789676885 56
1789676890 56
1789676895 56
1789676900 56
1789676905 56
1789676910 56
1789676915 56
1789676920 56
1789676925 56
1789676930 56
1789676935 64
1789676940 64
1789676945 64
1789676950 64
1789676955 64
1789676960 64
1789676965 64
```
</details>

---

