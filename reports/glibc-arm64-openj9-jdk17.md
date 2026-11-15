---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-15 11:58:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 11 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 11 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1794761747 48
1794761752 48
1794761757 48
1794761762 48
1794761767 46
1794761772 46
1794761777 46
1794761782 46
1794761787 46
1794761792 46
1794761797 46
1794761802 46
1794761807 46
1794761812 46
1794761817 46
1794761822 46
1794761827 46
1794761832 46
1794761837 46
1794761842 46
```
</details>

---

