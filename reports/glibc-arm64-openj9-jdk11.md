---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-27 13:58:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 7 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 345 |
| Sample Rate | 5.75/sec |
| Health Score | 359% |
| Threads | 12 |
| Allocations | 154 |

<details>
<summary>CPU Timeline (1 unique values: 36-36 cores)</summary>

```
1793123677 36
1793123682 36
1793123687 36
1793123692 36
1793123697 36
1793123702 36
1793123707 36
1793123712 36
1793123717 36
1793123722 36
1793123727 36
1793123732 36
1793123737 36
1793123742 36
1793123747 36
1793123752 36
1793123757 36
1793123762 36
1793123767 36
1793123772 36
```
</details>

---

