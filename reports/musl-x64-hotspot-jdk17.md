---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-28 10:04:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 564 |
| Sample Rate | 9.40/sec |
| Health Score | 588% |
| Threads | 9 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 704 |
| Sample Rate | 11.73/sec |
| Health Score | 733% |
| Threads | 11 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (5 unique values: 65-91 cores)</summary>

```
1777384893 91
1777384898 91
1777384903 85
1777384908 85
1777384913 85
1777384918 85
1777384923 85
1777384928 85
1777384933 85
1777384938 81
1777384943 81
1777384948 81
1777384953 81
1777384958 81
1777384963 81
1777384968 85
1777384973 85
1777384978 85
1777384983 80
1777384988 80
```
</details>

---

