---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-07 10:30:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 847 |
| Sample Rate | 14.12/sec |
| Health Score | 882% |
| Threads | 10 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (3 unique values: 67-71 cores)</summary>

```
1786112712 71
1786112717 71
1786112722 71
1786112727 71
1786112732 71
1786112737 67
1786112742 67
1786112747 67
1786112752 67
1786112757 67
1786112762 67
1786112767 67
1786112772 67
1786112777 67
1786112782 67
1786112787 67
1786112792 68
1786112797 68
1786112802 68
1786112807 68
```
</details>

---

