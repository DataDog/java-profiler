---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-19 22:04:17 EDT

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
| CPU Cores (start) | 12 |
| CPU Cores (end) | 12 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 9 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 172 |
| Sample Rate | 2.87/sec |
| Health Score | 179% |
| Threads | 10 |
| Allocations | 113 |

<details>
<summary>CPU Timeline (2 unique values: 11-12 cores)</summary>

```
1787191163 12
1787191168 12
1787191173 12
1787191178 12
1787191183 12
1787191188 12
1787191193 12
1787191198 12
1787191203 12
1787191208 12
1787191213 12
1787191218 12
1787191223 12
1787191228 11
1787191233 11
1787191238 11
1787191243 11
1787191248 11
1787191253 11
1787191258 11
```
</details>

---

