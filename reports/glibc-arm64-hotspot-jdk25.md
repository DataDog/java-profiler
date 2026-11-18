---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-18 07:14:54 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 11 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 10 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (3 unique values: 33-43 cores)</summary>

```
1795003842 43
1795003847 43
1795003852 43
1795003857 43
1795003862 43
1795003867 43
1795003872 43
1795003877 43
1795003882 43
1795003887 43
1795003892 43
1795003897 43
1795003902 43
1795003907 43
1795003912 43
1795003917 43
1795003922 43
1795003927 43
1795003932 38
1795003937 38
```
</details>

---

