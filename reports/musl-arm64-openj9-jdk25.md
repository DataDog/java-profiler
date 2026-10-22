---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-22 08:08:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 11 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 761 |
| Sample Rate | 12.68/sec |
| Health Score | 792% |
| Threads | 10 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1792670571 32
1792670576 32
1792670581 32
1792670586 32
1792670591 32
1792670596 32
1792670601 32
1792670606 32
1792670611 32
1792670617 32
1792670622 32
1792670627 32
1792670632 32
1792670637 32
1792670642 32
1792670647 32
1792670652 32
1792670657 32
1792670662 32
1792670667 32
```
</details>

---

