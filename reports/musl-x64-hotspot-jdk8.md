---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-30 09:38:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 183 |
| Sample Rate | 3.05/sec |
| Health Score | 191% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 231 |
| Sample Rate | 3.85/sec |
| Health Score | 241% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 38-51 cores)</summary>

```
1793367142 49
1793367147 49
1793367152 49
1793367157 49
1793367162 49
1793367167 49
1793367172 49
1793367177 49
1793367182 49
1793367187 49
1793367192 49
1793367197 49
1793367202 51
1793367207 51
1793367212 51
1793367217 51
1793367222 51
1793367227 48
1793367232 48
1793367237 48
```
</details>

---

