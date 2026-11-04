---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-04 12:28:13 EST

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
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 9 |
| Allocations | 39 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 917 |
| Sample Rate | 15.28/sec |
| Health Score | 955% |
| Threads | 11 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793812782 48
1793812787 48
1793812792 48
1793812797 48
1793812802 48
1793812807 48
1793812812 48
1793812817 48
1793812822 48
1793812827 48
1793812832 48
1793812837 48
1793812842 48
1793812847 48
1793812852 48
1793812857 48
1793812862 48
1793812867 48
1793812872 48
1793812877 48
```
</details>

---

