---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-29 11:52:33 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 9 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 723 |
| Sample Rate | 12.05/sec |
| Health Score | 753% |
| Threads | 10 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1790696787 48
1790696792 48
1790696797 48
1790696802 48
1790696807 48
1790696812 48
1790696817 48
1790696822 48
1790696827 48
1790696832 48
1790696837 48
1790696842 48
1790696847 48
1790696852 48
1790696857 48
1790696862 48
1790696867 48
1790696872 48
1790696877 48
1790696882 48
```
</details>

---

