---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-19 00:58:44 EDT

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 211 |
| Sample Rate | 3.52/sec |
| Health Score | 220% |
| Threads | 11 |
| Allocations | 180 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 13 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (2 unique values: 26-31 cores)</summary>

```
1789793667 31
1789793672 31
1789793677 31
1789793682 31
1789793687 31
1789793692 31
1789793697 31
1789793702 31
1789793707 26
1789793712 26
1789793717 26
1789793722 26
1789793727 26
1789793732 26
1789793737 26
1789793742 26
1789793747 26
1789793752 26
1789793757 26
1789793762 31
```
</details>

---

