---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-22 08:08:36 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 473 |
| Sample Rate | 7.88/sec |
| Health Score | 492% |
| Threads | 8 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 689 |
| Sample Rate | 11.48/sec |
| Health Score | 718% |
| Threads | 9 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1792670554 30
1792670559 30
1792670564 30
1792670569 30
1792670574 30
1792670579 30
1792670584 30
1792670589 30
1792670594 30
1792670599 30
1792670604 30
1792670609 32
1792670614 32
1792670619 32
1792670624 32
1792670629 32
1792670634 32
1792670639 32
1792670644 32
1792670649 32
```
</details>

---

