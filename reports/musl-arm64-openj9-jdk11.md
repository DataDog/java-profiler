---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 10:57:35 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 9 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 198 |
| Sample Rate | 3.30/sec |
| Health Score | 206% |
| Threads | 12 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1794498712 48
1794498717 48
1794498722 48
1794498727 48
1794498732 48
1794498737 48
1794498742 48
1794498747 48
1794498752 48
1794498757 48
1794498762 48
1794498767 48
1794498772 48
1794498777 48
1794498782 48
1794498787 48
1794498792 48
1794498797 48
1794498802 48
1794498807 48
```
</details>

---

