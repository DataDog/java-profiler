---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-24 05:28:59 EDT

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
| CPU Cores (start) | 16 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 11 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 10 |
| Allocations | 28 |

<details>
<summary>CPU Timeline (3 unique values: 16-52 cores)</summary>

```
1790241555 16
1790241560 16
1790241565 16
1790241570 16
1790241575 52
1790241580 52
1790241585 16
1790241590 16
1790241595 16
1790241600 16
1790241605 16
1790241610 16
1790241615 16
1790241620 16
1790241625 16
1790241630 16
1790241635 16
1790241640 16
1790241645 16
1790241650 16
```
</details>

---

