---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-02-03 09:53:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 605 |
| Sample Rate | 10.08/sec |
| Health Score | 630% |
| Threads | 8 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 862 |
| Sample Rate | 14.37/sec |
| Health Score | 898% |
| Threads | 11 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (4 unique values: 58-65 cores)</summary>

```
1770130063 58
1770130068 58
1770130073 58
1770130078 58
1770130083 58
1770130088 58
1770130093 60
1770130098 60
1770130103 60
1770130108 60
1770130113 60
1770130118 60
1770130123 65
1770130128 65
1770130133 65
1770130138 65
1770130143 65
1770130148 65
1770130153 65
1770130158 65
```
</details>

---

