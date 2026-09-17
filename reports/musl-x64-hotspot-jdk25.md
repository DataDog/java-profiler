---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-17 17:33:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 441 |
| Sample Rate | 7.35/sec |
| Health Score | 459% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 639 |
| Sample Rate | 10.65/sec |
| Health Score | 666% |
| Threads | 11 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (2 unique values: 75-81 cores)</summary>

```
1789680171 81
1789680176 81
1789680181 81
1789680186 81
1789680191 81
1789680196 81
1789680201 81
1789680206 81
1789680211 81
1789680216 81
1789680221 81
1789680226 81
1789680231 81
1789680236 81
1789680241 81
1789680246 75
1789680251 75
1789680256 75
1789680261 75
1789680266 75
```
</details>

---

