---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-27 13:58:51 EDT

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
| CPU Cores (start) | 55 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 8 |
| Allocations | 414 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 778 |
| Sample Rate | 12.97/sec |
| Health Score | 811% |
| Threads | 10 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (3 unique values: 55-73 cores)</summary>

```
1793123615 55
1793123620 55
1793123625 71
1793123630 71
1793123635 71
1793123640 71
1793123645 71
1793123650 71
1793123655 71
1793123660 71
1793123665 71
1793123670 71
1793123675 71
1793123680 73
1793123685 73
1793123690 71
1793123695 71
1793123700 71
1793123705 71
1793123710 71
```
</details>

---

