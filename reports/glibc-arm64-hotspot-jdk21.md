---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-21 09:08:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 8 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (2 unique values: 31-36 cores)</summary>

```
1789995835 36
1789995840 36
1789995845 36
1789995850 36
1789995855 36
1789995860 36
1789995865 36
1789995870 36
1789995875 36
1789995880 36
1789995885 36
1789995890 31
1789995895 31
1789995900 31
1789995905 31
1789995910 31
1789995915 31
1789995920 31
1789995925 31
1789995930 31
```
</details>

---

