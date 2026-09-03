---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-03 15:56:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 384 |
| Sample Rate | 6.40/sec |
| Health Score | 400% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 10 |
| Allocations | 67 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1788465030 43
1788465035 43
1788465040 43
1788465045 43
1788465050 43
1788465055 43
1788465060 43
1788465065 38
1788465070 38
1788465075 38
1788465080 38
1788465086 38
1788465091 38
1788465096 43
1788465101 43
1788465106 43
1788465111 43
1788465116 43
1788465121 43
1788465126 48
```
</details>

---

