---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-03 16:51:02 EST

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 574 |
| Sample Rate | 9.57/sec |
| Health Score | 598% |
| Threads | 8 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 794 |
| Sample Rate | 13.23/sec |
| Health Score | 827% |
| Threads | 10 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1793742138 81
1793742143 79
1793742148 79
1793742153 79
1793742158 79
1793742163 79
1793742168 79
1793742173 79
1793742178 79
1793742183 79
1793742188 79
1793742193 79
1793742198 79
1793742203 79
1793742208 79
1793742213 79
1793742218 79
1793742223 79
1793742228 79
1793742233 79
```
</details>

---

