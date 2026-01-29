---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-01-29 11:12:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 17.70/sec |
| Health Score | 1106% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ⚠️
| Metric | Value |
|--------|-------|
| Status | N/A |
| CPU Samples | N/A |
| Sample Rate | N/A/sec |
| Health Score | N/A% |
| Threads | N/A |
| Allocations | N/A |

<details>
<summary>CPU Timeline (3 unique values: 63-91 cores)</summary>

```
1769702698 63
1769702703 63
1769702708 63
1769702713 63
1769702718 63
1769702723 63
1769702728 63
1769702733 63
1769702738 63
1769702743 65
1769702748 65
1769702753 65
1769702758 65
1769702763 65
1769702768 65
1769702773 65
1769702778 65
1769702783 65
1769702788 65
1769702793 65
```
</details>

---

