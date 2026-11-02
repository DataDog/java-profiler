---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-01 20:32:53 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 219 |
| Sample Rate | 3.65/sec |
| Health Score | 228% |
| Threads | 12 |
| Allocations | 141 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 11 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1793582707 32
1793582712 32
1793582717 32
1793582722 32
1793582727 32
1793582732 32
1793582737 32
1793582742 32
1793582747 32
1793582752 32
1793582757 32
1793582762 32
1793582767 32
1793582772 32
1793582777 32
1793582782 32
1793582787 32
1793582792 32
1793582797 32
1793582802 32
```
</details>

---

