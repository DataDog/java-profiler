---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-21 17:43:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 482 |
| Sample Rate | 8.03/sec |
| Health Score | 502% |
| Threads | 8 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 768 |
| Sample Rate | 12.80/sec |
| Health Score | 800% |
| Threads | 9 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (2 unique values: 25-35 cores)</summary>

```
1790026693 35
1790026698 35
1790026703 35
1790026708 35
1790026713 35
1790026718 35
1790026723 35
1790026728 35
1790026733 35
1790026738 35
1790026743 35
1790026748 35
1790026753 35
1790026758 35
1790026763 35
1790026768 35
1790026773 25
1790026778 25
1790026783 25
1790026788 25
```
</details>

---

