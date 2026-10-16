---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-16 10:46:19 EDT

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 799 |
| Sample Rate | 13.32/sec |
| Health Score | 832% |
| Threads | 8 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1128 |
| Sample Rate | 18.80/sec |
| Health Score | 1175% |
| Threads | 10 |
| Allocations | 554 |

<details>
<summary>CPU Timeline (2 unique values: 28-32 cores)</summary>

```
1792161556 28
1792161561 28
1792161566 28
1792161571 28
1792161576 32
1792161581 32
1792161586 32
1792161591 32
1792161596 32
1792161601 32
1792161606 32
1792161611 32
1792161616 32
1792161621 32
1792161626 32
1792161631 32
1792161636 32
1792161641 32
1792161646 32
1792161651 32
```
</details>

---

