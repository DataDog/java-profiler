---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-21 15:32:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 16 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 10 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 14 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (2 unique values: 16-32 cores)</summary>

```
1790018802 16
1790018807 16
1790018812 16
1790018817 16
1790018822 16
1790018827 16
1790018832 16
1790018837 16
1790018842 16
1790018847 16
1790018852 16
1790018857 16
1790018862 16
1790018867 16
1790018872 16
1790018877 16
1790018882 16
1790018887 16
1790018892 16
1790018897 16
```
</details>

---

