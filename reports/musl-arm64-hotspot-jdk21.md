---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 05:53:53 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 10 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 250 |
| Sample Rate | 4.17/sec |
| Health Score | 261% |
| Threads | 14 |
| Allocations | 126 |

<details>
<summary>CPU Timeline (2 unique values: 26-30 cores)</summary>

```
1795603777 26
1795603782 26
1795603787 26
1795603792 26
1795603797 26
1795603802 26
1795603807 30
1795603812 30
1795603817 30
1795603822 30
1795603827 30
1795603832 30
1795603837 30
1795603842 30
1795603847 30
1795603852 30
1795603857 30
1795603862 30
1795603867 30
1795603872 30
```
</details>

---

