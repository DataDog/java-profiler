---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-28 11:22:31 EDT

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 28 |
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
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 685 |
| Sample Rate | 11.42/sec |
| Health Score | 714% |
| Threads | 9 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (3 unique values: 28-45 cores)</summary>

```
1777389437 45
1777389442 45
1777389447 45
1777389452 45
1777389457 45
1777389462 45
1777389467 45
1777389472 45
1777389477 45
1777389482 45
1777389487 40
1777389492 40
1777389497 40
1777389502 40
1777389507 40
1777389512 28
1777389517 28
1777389522 28
1777389527 28
1777389532 28
```
</details>

---

