---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-12 13:37:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 642 |
| Sample Rate | 10.70/sec |
| Health Score | 669% |
| Threads | 10 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (4 unique values: 50-55 cores)</summary>

```
1794508156 50
1794508161 50
1794508166 50
1794508171 50
1794508176 50
1794508181 50
1794508186 55
1794508191 55
1794508196 55
1794508201 55
1794508206 55
1794508211 55
1794508216 55
1794508221 55
1794508226 55
1794508231 55
1794508236 55
1794508241 55
1794508246 51
1794508251 51
```
</details>

---

