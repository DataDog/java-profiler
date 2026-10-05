---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-05 06:41:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 11 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (2 unique values: 31-51 cores)</summary>

```
1791196552 51
1791196557 51
1791196562 51
1791196567 51
1791196572 51
1791196577 51
1791196582 51
1791196587 51
1791196592 51
1791196597 51
1791196602 51
1791196607 51
1791196612 51
1791196617 51
1791196622 31
1791196627 31
1791196632 31
1791196637 31
1791196642 31
1791196647 31
```
</details>

---

