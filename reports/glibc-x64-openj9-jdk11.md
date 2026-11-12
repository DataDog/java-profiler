---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 13:37:07 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 8 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 694 |
| Sample Rate | 11.57/sec |
| Health Score | 723% |
| Threads | 9 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (2 unique values: 70-76 cores)</summary>

```
1794508176 70
1794508181 70
1794508186 70
1794508191 70
1794508196 70
1794508201 76
1794508206 76
1794508211 76
1794508216 76
1794508221 76
1794508226 76
1794508231 76
1794508236 76
1794508241 76
1794508246 76
1794508251 76
1794508256 76
1794508261 76
1794508266 76
1794508271 76
```
</details>

---

