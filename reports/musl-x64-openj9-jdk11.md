---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 13:46:07 EST

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 748 |
| Sample Rate | 12.47/sec |
| Health Score | 779% |
| Threads | 10 |
| Allocations | 549 |

<details>
<summary>CPU Timeline (3 unique values: 56-77 cores)</summary>

```
1795632021 70
1795632026 70
1795632031 70
1795632036 70
1795632041 70
1795632046 70
1795632051 70
1795632056 70
1795632061 70
1795632066 70
1795632071 70
1795632076 70
1795632081 70
1795632086 70
1795632091 70
1795632096 70
1795632101 70
1795632106 77
1795632111 77
1795632116 77
```
</details>

---

