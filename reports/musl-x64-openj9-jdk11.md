---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-17 11:33:35 EST

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 590 |
| Sample Rate | 9.83/sec |
| Health Score | 614% |
| Threads | 8 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 888 |
| Sample Rate | 14.80/sec |
| Health Score | 925% |
| Threads | 10 |
| Allocations | 551 |

<details>
<summary>CPU Timeline (2 unique values: 71-72 cores)</summary>

```
1794932970 71
1794932975 71
1794932980 71
1794932985 71
1794932990 71
1794932995 72
1794933000 72
1794933005 72
1794933010 72
1794933015 72
1794933020 72
1794933025 72
1794933030 72
1794933035 72
1794933040 72
1794933045 72
1794933050 72
1794933055 72
1794933060 72
1794933065 72
```
</details>

---

