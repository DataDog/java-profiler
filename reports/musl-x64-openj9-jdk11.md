---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-02 11:55:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 707 |
| Sample Rate | 11.78/sec |
| Health Score | 736% |
| Threads | 8 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 983 |
| Sample Rate | 16.38/sec |
| Health Score | 1024% |
| Threads | 11 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (2 unique values: 88-96 cores)</summary>

```
1788364252 96
1788364257 96
1788364262 96
1788364267 96
1788364272 96
1788364277 96
1788364282 96
1788364287 96
1788364292 96
1788364297 96
1788364302 96
1788364307 96
1788364312 96
1788364317 96
1788364322 88
1788364327 88
1788364332 88
1788364337 88
1788364342 88
1788364347 88
```
</details>

---

