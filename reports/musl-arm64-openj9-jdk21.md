---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-31 06:53:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 22 |
| Sample Rate | 0.37/sec |
| Health Score | 23% |
| Threads | 10 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793443762 48
1793443767 48
1793443772 48
1793443777 48
1793443782 48
1793443787 48
1793443792 48
1793443797 48
1793443802 48
1793443807 48
1793443812 48
1793443817 48
1793443822 48
1793443827 48
1793443832 48
1793443837 48
1793443842 48
1793443847 48
1793443852 43
1793443857 43
```
</details>

---

