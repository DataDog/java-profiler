---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-30 14:54:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 538 |
| Sample Rate | 8.97/sec |
| Health Score | 561% |
| Threads | 8 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 796 |
| Sample Rate | 13.27/sec |
| Health Score | 829% |
| Threads | 10 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (3 unique values: 28-32 cores)</summary>

```
1777575023 32
1777575028 32
1777575033 32
1777575038 32
1777575043 32
1777575048 32
1777575053 32
1777575058 32
1777575063 30
1777575068 30
1777575073 30
1777575078 30
1777575083 30
1777575088 30
1777575093 30
1777575098 30
1777575103 30
1777575108 30
1777575113 28
1777575118 28
```
</details>

---

