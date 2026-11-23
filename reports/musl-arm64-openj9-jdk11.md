---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-23 04:42:47 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 10 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795426668 64
1795426673 64
1795426678 64
1795426683 64
1795426689 64
1795426694 64
1795426699 64
1795426704 64
1795426709 64
1795426714 64
1795426719 64
1795426724 64
1795426729 64
1795426734 64
1795426739 64
1795426744 64
1795426749 64
1795426754 64
1795426759 64
1795426764 64
```
</details>

---

