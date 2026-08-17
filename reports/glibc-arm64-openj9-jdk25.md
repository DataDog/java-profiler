---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-17 16:55:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
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
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 9 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 14 |
| Allocations | 78 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1786999816 48
1786999821 48
1786999826 46
1786999831 46
1786999836 46
1786999841 46
1786999846 46
1786999851 46
1786999857 46
1786999862 46
1786999867 46
1786999872 48
1786999877 48
1786999882 48
1786999887 48
1786999892 48
1786999897 48
1786999902 48
1786999907 48
1786999912 48
```
</details>

---

