---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-26 10:28:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 9 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 7 |
| Allocations | 23 |

<details>
<summary>CPU Timeline (2 unique values: 39-44 cores)</summary>

```
1795706683 39
1795706688 39
1795706693 39
1795706698 39
1795706703 39
1795706708 39
1795706713 39
1795706718 39
1795706723 39
1795706728 39
1795706733 44
1795706738 44
1795706743 44
1795706748 44
1795706753 44
1795706759 44
1795706764 44
1795706769 44
1795706774 44
1795706779 44
```
</details>

---

