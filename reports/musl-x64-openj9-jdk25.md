---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-19 12:22:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 13 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 368 |
| Sample Rate | 6.13/sec |
| Health Score | 383% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 593 |
| Sample Rate | 9.88/sec |
| Health Score | 618% |
| Threads | 10 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (3 unique values: 13-32 cores)</summary>

```
1792426644 13
1792426649 30
1792426654 30
1792426659 30
1792426664 30
1792426669 32
1792426674 32
1792426679 32
1792426684 32
1792426689 32
1792426694 32
1792426699 32
1792426704 32
1792426709 32
1792426714 32
1792426719 32
1792426724 32
1792426729 32
1792426735 32
1792426740 32
```
</details>

---

