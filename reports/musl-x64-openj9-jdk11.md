---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-03-11 16:37:28 EDT

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
| CPU Cores (start) | 23 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 621 |
| Sample Rate | 10.35/sec |
| Health Score | 647% |
| Threads | 8 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 858 |
| Sample Rate | 14.30/sec |
| Health Score | 894% |
| Threads | 9 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (4 unique values: 23-28 cores)</summary>

```
1773261141 23
1773261146 23
1773261151 23
1773261156 23
1773261161 23
1773261166 23
1773261171 23
1773261176 23
1773261181 23
1773261186 23
1773261191 23
1773261196 23
1773261201 23
1773261206 28
1773261211 28
1773261216 28
1773261221 28
1773261226 28
1773261231 28
1773261236 28
```
</details>

---

