---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-17 17:33:14 EDT

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 575 |
| Sample Rate | 9.58/sec |
| Health Score | 599% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 807 |
| Sample Rate | 13.45/sec |
| Health Score | 841% |
| Threads | 9 |
| Allocations | 547 |

<details>
<summary>CPU Timeline (5 unique values: 72-84 cores)</summary>

```
1789680176 72
1789680181 84
1789680186 84
1789680191 84
1789680196 84
1789680201 84
1789680206 84
1789680211 84
1789680216 84
1789680221 82
1789680226 82
1789680231 82
1789680236 82
1789680241 82
1789680246 82
1789680251 82
1789680256 82
1789680261 82
1789680266 73
1789680271 73
```
</details>

---

