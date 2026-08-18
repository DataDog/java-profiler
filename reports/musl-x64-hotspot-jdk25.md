---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-18 08:24:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 499 |
| Sample Rate | 8.32/sec |
| Health Score | 520% |
| Threads | 9 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 603 |
| Sample Rate | 10.05/sec |
| Health Score | 628% |
| Threads | 10 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1787055546 79
1787055551 79
1787055556 81
1787055561 81
1787055566 81
1787055571 81
1787055576 81
1787055581 81
1787055586 81
1787055591 81
1787055596 81
1787055601 81
1787055606 81
1787055611 81
1787055616 81
1787055621 81
1787055626 81
1787055631 81
1787055636 81
1787055641 81
```
</details>

---

