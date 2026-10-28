---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-28 11:29:54 EDT

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
| CPU Samples | 377 |
| Sample Rate | 6.28/sec |
| Health Score | 392% |
| Threads | 9 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 203 |
| Sample Rate | 3.38/sec |
| Health Score | 211% |
| Threads | 12 |
| Allocations | 110 |

<details>
<summary>CPU Timeline (3 unique values: 46-48 cores)</summary>

```
1793201078 48
1793201083 48
1793201088 46
1793201093 46
1793201098 46
1793201103 46
1793201108 46
1793201113 46
1793201118 46
1793201123 46
1793201128 48
1793201133 48
1793201138 48
1793201143 48
1793201148 47
1793201153 47
1793201158 47
1793201163 47
1793201168 47
1793201173 47
```
</details>

---

