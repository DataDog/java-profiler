---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-27 13:59:55 EDT

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 8 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 698 |
| Sample Rate | 11.63/sec |
| Health Score | 727% |
| Threads | 9 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (4 unique values: 72-76 cores)</summary>

```
1793123667 73
1793123672 73
1793123677 73
1793123682 76
1793123687 76
1793123692 74
1793123697 74
1793123702 74
1793123707 74
1793123712 74
1793123717 74
1793123722 72
1793123727 72
1793123732 72
1793123737 72
1793123742 72
1793123747 72
1793123752 72
1793123757 72
1793123762 72
```
</details>

---

