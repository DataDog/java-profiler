---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-26 14:59:54 EDT

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 10 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 274 |
| Sample Rate | 4.57/sec |
| Health Score | 286% |
| Threads | 13 |
| Allocations | 174 |

<details>
<summary>CPU Timeline (3 unique values: 39-52 cores)</summary>

```
1793040998 39
1793041004 39
1793041009 39
1793041014 39
1793041019 39
1793041024 39
1793041029 39
1793041034 39
1793041039 39
1793041044 52
1793041049 52
1793041054 52
1793041059 52
1793041064 52
1793041069 41
1793041074 41
1793041079 41
1793041084 41
1793041089 41
1793041094 41
```
</details>

---

