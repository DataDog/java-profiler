---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-24 08:33:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 403 |
| Sample Rate | 6.72/sec |
| Health Score | 420% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 9 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (3 unique values: 21-30 cores)</summary>

```
1777033718 30
1777033723 30
1777033728 30
1777033733 30
1777033738 30
1777033743 30
1777033748 26
1777033753 26
1777033758 26
1777033763 26
1777033768 26
1777033773 26
1777033778 26
1777033783 26
1777033788 26
1777033793 26
1777033798 21
1777033803 21
1777033808 21
1777033813 21
```
</details>

---

