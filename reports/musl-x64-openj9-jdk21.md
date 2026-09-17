---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-17 17:33:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 491 |
| Sample Rate | 8.18/sec |
| Health Score | 511% |
| Threads | 9 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 702 |
| Sample Rate | 11.70/sec |
| Health Score | 731% |
| Threads | 11 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (2 unique values: 90-96 cores)</summary>

```
1789680176 96
1789680181 96
1789680186 96
1789680191 96
1789680196 96
1789680201 96
1789680206 96
1789680211 96
1789680216 96
1789680221 96
1789680226 96
1789680231 96
1789680236 96
1789680241 96
1789680246 96
1789680251 90
1789680256 90
1789680261 90
1789680266 90
1789680271 90
```
</details>

---

