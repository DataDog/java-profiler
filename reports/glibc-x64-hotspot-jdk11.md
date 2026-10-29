---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-29 09:55:38 EDT

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
| CPU Cores (start) | 78 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 752 |
| Sample Rate | 12.53/sec |
| Health Score | 783% |
| Threads | 10 |
| Allocations | 538 |

<details>
<summary>CPU Timeline (2 unique values: 76-78 cores)</summary>

```
1793281807 78
1793281812 78
1793281817 78
1793281822 78
1793281827 78
1793281832 78
1793281837 78
1793281842 78
1793281847 78
1793281852 78
1793281857 78
1793281862 78
1793281867 78
1793281872 78
1793281877 78
1793281882 78
1793281887 78
1793281892 78
1793281897 76
1793281902 76
```
</details>

---

