---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-02-03 08:38:43 EST

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 603 |
| Sample Rate | 10.05/sec |
| Health Score | 628% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 685 |
| Sample Rate | 11.42/sec |
| Health Score | 714% |
| Threads | 11 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (3 unique values: 27-32 cores)</summary>

```
1770125644 31
1770125649 31
1770125654 32
1770125659 32
1770125664 32
1770125669 32
1770125674 32
1770125679 32
1770125684 32
1770125689 32
1770125694 32
1770125699 32
1770125704 32
1770125709 32
1770125714 32
1770125719 32
1770125724 32
1770125729 32
1770125734 32
1770125739 32
```
</details>

---

