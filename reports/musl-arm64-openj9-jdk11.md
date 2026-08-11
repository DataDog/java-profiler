---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-11 12:25:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 663 |
| Sample Rate | 11.05/sec |
| Health Score | 691% |
| Threads | 8 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 13 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (2 unique values: 21-26 cores)</summary>

```
1786465165 26
1786465170 26
1786465175 26
1786465180 26
1786465185 26
1786465190 26
1786465195 26
1786465200 26
1786465205 26
1786465210 26
1786465215 26
1786465220 26
1786465225 21
1786465230 21
1786465235 21
1786465240 21
1786465245 21
1786465250 21
1786465255 21
1786465260 21
```
</details>

---

