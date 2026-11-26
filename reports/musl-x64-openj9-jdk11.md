---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-26 06:52:56 EST

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
| CPU Cores (start) | 83 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 139 |
| Sample Rate | 2.32/sec |
| Health Score | 145% |
| Threads | 11 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 6 |
| Allocations | 4 |

<details>
<summary>CPU Timeline (3 unique values: 59-83 cores)</summary>

```
1795693702 83
1795693707 83
1795693712 83
1795693717 81
1795693722 81
1795693727 81
1795693732 81
1795693737 81
1795693742 81
1795693747 81
1795693752 81
1795693757 81
1795693762 81
1795693767 81
1795693772 81
1795693777 81
1795693782 81
1795693787 81
1795693792 81
1795693797 81
```
</details>

---

