---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-18 04:34:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 639 |
| Sample Rate | 10.65/sec |
| Health Score | 666% |
| Threads | 11 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (2 unique values: 61-96 cores)</summary>

```
1789719908 96
1789719913 96
1789719918 96
1789719923 61
1789719928 61
1789719933 61
1789719938 61
1789719943 61
1789719948 61
1789719953 61
1789719958 61
1789719963 61
1789719968 61
1789719973 61
1789719978 61
1789719983 61
1789719988 61
1789719993 61
1789719998 61
1789720003 61
```
</details>

---

