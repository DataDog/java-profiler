---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-11 23:07:43 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 13 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1791774151 64
1791774156 64
1791774161 64
1791774166 64
1791774171 64
1791774176 64
1791774181 64
1791774186 64
1791774191 64
1791774196 64
1791774201 64
1791774206 64
1791774211 64
1791774216 64
1791774221 59
1791774226 59
1791774231 59
1791774236 59
1791774241 59
1791774246 59
```
</details>

---

