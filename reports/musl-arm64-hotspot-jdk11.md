---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-23 11:58:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 9 |
| Allocations | 42 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 9 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1795452822 64
1795452827 64
1795452832 64
1795452837 64
1795452842 64
1795452847 64
1795452852 64
1795452857 64
1795452862 64
1795452867 64
1795452872 64
1795452877 64
1795452882 64
1795452887 64
1795452892 59
1795452897 59
1795452902 59
1795452907 59
1795452912 59
1795452917 59
```
</details>

---

