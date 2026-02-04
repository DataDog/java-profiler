---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-04 13:27:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 11 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 783 |
| Sample Rate | 13.05/sec |
| Health Score | 816% |
| Threads | 12 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1770229079 46
1770229084 46
1770229089 46
1770229094 46
1770229099 46
1770229104 46
1770229109 46
1770229114 46
1770229119 46
1770229124 46
1770229129 46
1770229134 46
1770229139 46
1770229144 48
1770229149 48
1770229154 48
1770229159 48
1770229164 48
1770229169 48
1770229174 48
```
</details>

---

