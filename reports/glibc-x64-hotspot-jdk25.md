---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-30 19:50:54 EDT

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
| CPU Cores (start) | 57 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 9 |
| Allocations | 417 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 698 |
| Sample Rate | 11.63/sec |
| Health Score | 727% |
| Threads | 12 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (7 unique values: 57-83 cores)</summary>

```
1777592818 57
1777592823 57
1777592828 61
1777592833 61
1777592838 58
1777592843 58
1777592848 63
1777592853 63
1777592858 63
1777592863 63
1777592868 63
1777592873 63
1777592878 73
1777592883 73
1777592888 73
1777592893 73
1777592898 78
1777592903 78
1777592908 83
1777592913 83
```
</details>

---

